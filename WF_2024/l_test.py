import argparse
import subprocess
import re
import sys
from typing import TextIO, Tuple


MAX = 101
ROT_LEFT = {'S':'E', 'N':'W', 'E':'N', 'W':'S'}
MOVES = {"N": (-1, 0), "S": (1, 0), "W": (0, -1), "E": (0, 1)}
cnt = 0


class WrongAnswer(RuntimeError):
    """Raised whenever an incorrect answer is received."""
    pass


def vprint(*args, verbose: bool, file: TextIO, **kwargs) -> None:
    """Print to `file`, and also to stdout if `verbose is true."""
    if verbose:
        print("< ", end="")
        print(*args, **kwargs)
        sys.stdout.flush()
    print(*args, file=file, flush=True, **kwargs)


def vreadline(data: TextIO, *, verbose: bool) -> str:
    """Read a line from `data`, and also log it to stdout if `verbose` is true."""
    line = data.readline()
    if verbose and line:
        print(">", line.rstrip("\n"))
    return line


def interact(process: subprocess.Popen, input_data: Tuple, *, verbose: bool) -> int:
    num_rows, num_cols, maze, row, col, dir = input_data

    def has_wall(r, c):
        if r < 1 or r > num_rows or c < 1 or c > num_cols:
            return True
        return maze[r-1][c-1] == '#'

    def to_wall(r, c, d):
        for i in range(MAX):
            if has_wall(r + i*MOVES[d][0], c + i*MOVES[d][1]):
                return i-1

    vprint(num_rows, num_cols, file=process.stdin, verbose=verbose)
    for row_str in maze:
        vprint(row_str, file=process.stdin, verbose=verbose)

    try:
        while True:
            vprint(to_wall(row, col, dir), file=process.stdin, verbose=verbose)
            move = vreadline(process.stdout, verbose=verbose)
            if move == "":
                raise WrongAnswer("End of file received from team program")
            move = move.strip().lower()
            if move == "":  # Blank line
                continue

            if move == "no":
                print(f"Team program stopped with 'no' at ({row}, {col}) facing {dir}")
                return

            if re.match("yes\s+[0-9]\s+[0-9]+", move):
                r_out, c_out = map(int, move.split()[1:])
                if (r_out, c_out) != (row, col):
                    raise WrongAnswer(
                        f"Team program claims we are at ({r_out}, {c_out}), but current location is ({row}, {col})"
                    )
                print(f"Team program stopped with 'yes {r_out} {c_out}' at ({row}, {col}) facing {dir}")
                return

            if move == 'left':
                dir = ROT_LEFT[dir]
            elif move == 'right':
                dir = ROT_LEFT[dir]
                dir = ROT_LEFT[dir]
                dir = ROT_LEFT[dir]
            elif move == 'step':
                row += MOVES[dir][0]
                col += MOVES[dir][1]
                if has_wall(row, col):
                    raise WrongAnswer(
                        f"Stepped into wall at ({row}, {col})"
                    )
            else:
                raise WrongAnswer(
                    f"Invalid move produced by the program: {move}"
                )
    except BrokenPipeError:
        raise WrongAnswer("Error when sending response to team program - possibly exited")


def main() -> int:
    parser = argparse.ArgumentParser(
        usage="%(prog)s [--verbose] data.in program [args...]"
    )
    parser.add_argument(
        "--verbose", "-v", action="store_true", help="Show interactions"
    )
    parser.add_argument("data")
    parser.add_argument("program", nargs=argparse.REMAINDER)

    args = parser.parse_args()
    if not args.program:
        parser.error("Must specify program to run")

    with open(args.data, "r") as data:
        num_rows, num_cols = map(
            int, data.readline().strip("\n").split()
        )
        if not (1 <= num_rows <= MAX and 1 <= num_cols <= MAX):
            raise ValueError(
                f"Map dimensions out of bounds. Got ({num_rows}, {num_cols}), but both must be in range [1, {MAX}]"
            )

        maze = [data.readline().strip("\n") for _ in range(num_rows)]
        for row_num, row_str in enumerate(maze):
            if len(row_str) != num_cols:
                raise ValueError(
                    f"Row {row_num + 1} does not have expected length {num_cols}, has length {len(row_str)}"
                )
            if any(c not in "#." for c in row_str):
                raise ValueError(
                    f"Row {row_num + 1} has invalid characters (only . and # allowed)."
                )

        row_s, col_s, dir = data.readline().strip("\n").split()
        row, col = int(row_s), int(col_s)
        if not (1 <= row <= num_rows and 1 <= col <= num_cols):
            raise ValueError("Start position is out of bounds")
        if dir not in ROT_LEFT:
            raise ValueError(f"Start direction invalid, got {dir}, but must be one of N,S,E,W")

        input_data = (num_rows, num_cols, maze, row, col, dir)

    process = subprocess.Popen(
        args.program,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        encoding="utf-8",
        errors="surrogateescape",
    )
    try:
        interact(process, input_data, verbose=args.verbose)
        process.wait()
    except WrongAnswer as exc:
        print(f"Wrong answer: {exc}")
        return 1
    finally:
        if process.poll() is None:
            try:
                process.terminate()
            except ProcessLookupError:  # Should be impossible, but just to be safe
                pass
        process.wait()

    if process.returncode < 0:
        print(f'Run-time error (process exited with signal {-process.returncode})')
        return 1
    elif process.returncode > 0:
        print(f'Run-time error (process exited with status {process.returncode})')
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())