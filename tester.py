import subprocess
from subprocess import Popen, PIPE, STDOUT
import os
import argparse

# Update number here if you add more tests
N_tests = 13

def run_tests(outputfile):
    # First make pa3tests

    # print('Make pa3...'),
    # subprocess.call(['make', 'pa3'], stdout=PIPE)
    # print('Done.')

    print('Make pa3tests...'),
    subprocess.call(['make', 'pa3tests'], stdout=PIPE)
    print('Done.')

    print('Running all tests...')

    with open(outputfile, 'w') as outFile:
        # Then run all tests
        for i in range(1, N_tests+1):
            print("Run test " + str(i))
            outFile.write('\n-----TEST' + str(i) + '-----\n')
            outFile.flush()
            cmd = ['./pa3tests']
            my_env = os.environ.copy()
            my_env["N"] = str(i)
            result = Popen(cmd, stdout=outFile, stderr=STDOUT, env=my_env).wait()
            outFile.flush()
            outFile.write('\n----------------\n')
            outFile.flush()
        print("All done.")

def extract_result_roadtraces(test_result_file, roadtrace_filename):
    """
    Use this to dump out pa3tests_result.txt to a new file with only road traces
    """
    with open(test_result_file, 'r') as inFile:
        lines = inFile.read().splitlines()
        road_traces = list(enumerate([l for l in lines if 'Road Trace' in l]))

        num_success_runs = len([l for l in lines if 'System exiting (normal)' in l])
        
        if num_success_runs != N_tests:
            raise Exception("\nSome tests can't be run successfully. Please fix them first. ABORT\n")
        else:
            print('All runs are successful. Generating road traces...')

        with open(roadtrace_filename, 'w') as keyFile:
            keyFileOutput = '\n'.join([str(i+1) + " " + t for i, t in road_traces])
            keyFile.write(keyFileOutput)
            print(keyFileOutput)
            print('\nWrote key to ' + roadtrace_filename + '.')


def compare_target_and_key(targetfile, keyfile):
    with open(targetfile, 'r') as target, open(keyfile, 'r') as key:
        target_lines = target.read().splitlines()
        key_lines = key.read().splitlines()

        count_all = 0
        count_diff = 0
        for i, (t, k) in enumerate(zip(target_lines ,key_lines)):
            if t != k:
                print(str(i+1) + ' DIFF')
                print('\tTarget = ' + t)
                print('\tKey = ' + k)

                count_diff += 1
            else:
                print(str(i+1) + ' Same')
            
            count_all += 1

        print("\nRESULT: " + str(count_diff) + " difference(s) out of " + str(count_all) + " tests.")


parser = argparse.ArgumentParser()

# dest is important so we can distinguish which sub-command it is
subparsers = parser.add_subparsers(dest='which')
subparsers.required = True

parser_runtests = subparsers.add_parser('runtests', help='Run all tests, write output and a road trace file. Can also be used to generate key.')
parser_runtests.add_argument('-k', '--key', help='Key mode, generate outputs and traces to be used as answer key', action='store_true')

parser_comparetraces = subparsers.add_parser('compare', help='Compare my (target) traces with key traes')

args = parser.parse_args()

print(args)


if args.which == 'runtests':

    if not os.path.exists('./tester'):
        os.makedirs('./tester')
        print("Folder 'testers' created.")
    else:
        print("Folder 'testers' already exists.")

    is_keymode = args.key
    if is_keymode:
        print("\nRun tests in key mode...\n")
        run_tests('./tester/key_outputs.txt')
        extract_result_roadtraces('./tester/key_outputs.txt', './tester/key_roadtraces.txt')
    else:
        print("\nRun tests in normal mode...\n")
        run_tests('./tester/test_outputs.txt')
        extract_result_roadtraces('./tester/test_outputs.txt', './tester/test_roadtraces.txt')

elif args.which == 'compare':

    if not os.path.exists('./tester/test_roadtraces.txt'):
        raise Exception('Target road traces not found. Run `python tester.py runtests` to run tests first.')

    if not os.path.exists('./tester/key_roadtraces.txt'):
        raise Exception('Key road traces not found. Either place an existing key or run `python tester.py runtests --key` to generate new key from current output.')

    compare_target_and_key('./tester/test_roadtraces.txt', './tester/key_roadtraces.txt')