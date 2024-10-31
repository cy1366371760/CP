#!/usr/bin/env python3
#
# Testing tool for the Going in Circles problem
#
# Usage:
#
#   python3 testing_tool.py [-s sequence] <program>
#
# The sequence must consist of characters '0' and '1' and have length at least 3.
# If no initial sequence is specified, the sample (011) is used.
#
# You can compile and run your solution as follows.
# - You may have to replace 'python3' by just 'python'.
# - On Windows, you may have to replace '/' by '\'.
#
# If you have a Java solution that you would run using
# "java MyClass", you could invoke the testing tool with:
#
#   python3 testing_tool.py java MyClass
#
# If you have a Python solution that you would run using
# "python solution.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py python solution.py
#
# If you have a C++ solution stored in a file called "sol.cpp",
# you must first compile using "g++ sol.cpp -o sol" and then
# invoke the testing tool with:
#
#   python3 testing_tool.py ./sol
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it
# is not guaranteed that a program that passes the testing tool
# will be accepted.
#
import argparse
import subprocess
import sys
import traceback


def write(p, line):
    assert p.poll() is None, 'Program terminated early'
    print('Write: {}'.format(line), flush=True)
    p.stdin.write('{}\n'.format(line))
    p.stdin.flush()


def read(p):
    assert p.poll() is None, 'Program terminated early'
    line = p.stdout.readline().strip()
    assert line != '', 'Read empty line or closed output pipe. Make sure that your program started successfully.'
    print('Read: %s' % line, flush=True)
    return line


def wrong_answer(p, reason):
    sys.stdout.write('%s\n' % reason)
    p.kill()


parser = argparse.ArgumentParser(description='Testing tool for the Going in Circles problem')
parser.add_argument('-s', dest='sequence', metavar='sequence', default="11100000110100111100111101100110010111111010110101110000000100101110010111101011101111101001100001001110101100111110010001001010000100111011010100011000110110101010000000001000011111011101100011100110010001111111100101111010110101000011111101101000110001111110111011001111000100000001010101111111101010000001001110001100111100111011100000110010100011101000111110111111111101010000111001010010100001001011011001011001010000010001011110001101010100011100011100101100111101110010110110111100000000010101101101110001101101111100010111100011001110111100101100001001001000011100100101000011011000111010011111111011110101010010011010111100100111101111100101111101100010010110111011000110111001101001101100100001101011100100111111001110011101010110100100000111101011100001110010110010100000000111111110011110111001001110110010000000001101100101111111001000100000110001011101000011001010100111101110111011001100010101000110101100000101010100000010101101001001111011110000100110101101011111001100001110010101101100010000011100111010010000110100100000000111110110000100101110011101101000000110011010001001001011100011101000001010110111010101111110000110010000100010010101000000100101101110111110000001101100110110010111100101011010111111011011001001101010000101011110001100100011100010100110001101010011000111101011110001110000001111111100110101010101001100100111000010101100000110011001011011111000010110010010000101100011101010000111010111010110110111000110011111010100100100110101000010100011111001111010110001101001010001110100110011010111100110001100111001010101100001101010100111010110010001111011011100101111000001110001011001011101110110100111011000110100101000000011110001110010111101111111100011001001111110100001111111000011101110100010001100111110001101111101011110001001111111001001101000111000010000100011000001000110111111110010100001101000000110111010011000001111110011010000111110001111000001001010001110001010100010001100111000010010111011111100111111110011010110001001101011010001111100011100111010000001001100110010111110110010101010111001000110001110011001111101110001001111000101011101110000111110010010111011010110010011001110101000001001011101000100101010110011110100011010100111000001110100011110001110001101110010110000100010010000100010010000011101000001101010101111110101111110010111010010110110011111101000000111110100111110111010111010000011010001100110101110010110111100111001000110000110010101110010010001100110001111010100100111000111111001100001101100111111111110101110011001000100000000111111011110010101001011001100011110110111101100111010100111101111111010111100010000110000010111110010111111100001110010010111110111111100111110100000110101001010101100000010100010101100011101101111010011100101111001001011110110101100001100001000110110011110010110111111000000100111110000100010100000111001011011001001101101110101000001110110101110010110101000110101001100110101110000101111000010100110001011001001111101001111110101101010111101011001101110001001011101001001110011000001100111011111010011010010000100011001100011000001101010001011000100011000111100110111010010101101101101010111010100111110110001100000011111101101000011001101100010000001011111001010001111000101111110110010110011011110011100100101110101011010011101011011000001001001001101100101110101011010100100010001101010010001111000000011110001000011000100111100000011110001001111000100111001111110001111101000000000001001000111110100001000001110001000011011001011001000001111110001010001001011011011100100100011011000000100001111111111111010010100111010001111110101111010000011110001010011100001101011011000111011111100110010000110110100101111110110110111010000011000101111110111001101011101110000010000101110111111001010111101100101001110001110100000001010010110010010001011010100011111100110101111111100000111110111101111110111110001110001011000001010101111001110010101000001111100110110110011001001010011000000111001001000001100111111000000111011111001100011110111100110110000010000001101101101001100101010100100101010000100010110000010111111001100111100010100111110010110110011001110000101011010100110010100111111110010011101010110101110111010011000101000010111001001111100011111100010010110001111111001111011011010110110011000001000110001010000010111000110010101011011101011111001101110000011100100110000101101101101111100010011010101001011101100001100100111111010101100110011010000110101111111111101011110101110001010000110001011011101000011001100100001010000001101011010110101011001001101100111011111101110001000111110001001100000000111010111111111110011100110111101001000101110000000000100000110111000101000100111100001010010001000111111111110100110111110100110111010010011011101001011110110111011000110000011010010010010100000001100100001011010001111000010011100000001010100101010011001011010110111010001101110111000010111110010001011110111101001001011000011111000011110011011100111111110111010011110000110110000001101000111111000110011110011101101101100010101110011100000000010101100101000010011010111110111")
parser.add_argument('program', nargs='+', help='Invocation of your solution')

args = parser.parse_args()

sequence = list(args.sequence)
for c in sequence:
    assert c in '01', f'Character {c} may not appear in the input sequence.'
n = len(sequence)
assert n >= 3, f'Sequence must have length at least 3'
position = 0

queries = 0
queries_limit = 3 * n + 500

with subprocess.Popen(" ".join(args.program), shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE,
                      universal_newlines=True) as p:
    try:
        write(p, sequence[position])

        while True:
            response = read(p)

            if response.startswith('? '):
                if queries == 50000:
                    wrong_answer(p, 'Program used too many queries, aborting')
                    break
                queries += 1
                action = response[2:]
                if action == 'right':
                    position = (position + 1) % n
                elif action == 'left':
                    position = (position - 1) % n
                elif action == 'flip':
                    sequence[position] = str(1 - int(sequence[position]))
                else:
                    wrong_answer(p, 'Program gave unrecognized action')
            elif response.startswith('! '):
                answer = response[2:]
                assert answer.isnumeric(), 'Expected final guess to be a positive integer'
                answer = int(answer)
                if answer == n:
                    assert queries <= queries_limit, 'Program printed correct solution, but used too many queries'
                    assert p.stdout.readline() == '', 'Printed extra data after finding solution'
                    assert p.wait() == 0, 'Did not exit cleanly after finishing'
                    break
                else:
                    wrong_answer(p, 'Program printed incorrect solution')
                    break
            else:
                wrong_answer(p, 'Program gave invalid response')
                break

            write(p, sequence[position])
    except:
        traceback.print_exc()
    finally:
        sys.stdout.flush()
        sys.stderr.flush()
        sys.stdout.write(f'Used {queries} queries, limit is {queries_limit}.\nProgram exit code: {p.wait()}\n')
        sys.stdout.flush()