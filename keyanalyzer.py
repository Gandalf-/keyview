#!/usr/bin/python

# keyanalyzer.py
#   Author: Austin Voecks

# example usage:
#   python keyanalyzer.py ~/.keyview.log 50 1-5

import sys, operator, time

CNT = 0
LEN = 1

help_text = \
    'h         : help\n'\
    'q         : quit\n'\
    'c         : clear\n'\
    'r int-int : set substring size range\n'\
    's int     : set number of results\n'\
    'd         : default query\n'\
    'm str ... : query, results must match provided input\n'\
    'n str ... : query, results must match any of provided input\n'\
    'f str ... : query, results must not match provided input\n'\
    't str     : query, results must match provided input exactly\n'

def get_substrings(lines, range_start, range_end):
    ''' list of strings, int, int -> dict of strings to lists of ints

    fills a dictionary with the frequencies of substrings, where the substrings
    are sizes from @range_start to @range_end. this is completed in one pass

    tab is used as the delimiter between characters in substrings
    '''
    substrings = {}
    lengths = xrange(range_start, range_end)

    for line_index in xrange(len(lines)):
        base = '\t'.join(lines[line_index:line_index + range_start])

        for length in lengths:
            try:
                substrings[base][CNT] += 1
            except KeyError:
                substrings[base] = [1, length]

            try:
                base += '\t' + lines[line_index + length]
            except IndexError:
                pass

    return substrings


def get_total(substrings):
    ''' dict of strings to lists of ints -> float

    sum all substrings (characters) of size 1
    '''
    total = 0.0

    for key in substrings:
        if substrings[key][LEN] == 1:
            total += substrings[key][CNT]

    return total


def shorthand(substring):
    ''' string -> string

    condenses duplicate instances in the substring
    ctl_p bks bks bks -> ctl_p bks x3
    '''
    out     = ''
    keys    = substring.split('\t')
    printed = []

    for key in keys:
        if key not in printed:
            cnt = keys.count(key)
            printed.append(key)

            if cnt > 1:
                out += key + ' x' + str(cnt) + ' '
            else:
                out += key + ' '

    return out


def print_substrings(sorted_substrings, num_results, total_keys):
    ''' dict of strings to lists of ints, float -> IO
    '''
    for substring in sorted_substrings[-num_results:][::-1]:

        key_sequence   = shorthand(substring[0])
        sequence_count = substring[1][CNT]

        if total_keys:
            ratio = (substring[1][CNT] / total_keys) * 100
            print("%-50s%-15d%6.2f" % (key_sequence[:50], sequence_count, ratio))

        else:
            print("%-50s%-15d" % (key_sequence[:50], sequence_count))


def filter_dict(condition, d):
    ''' function, dict -> dict
    '''
    return dict([[key, d[key]] for key in d.keys() if condition(key)])


def main():
    ''' string -> IO
    '''
    # arguments
    try:
        file_name = sys.argv[1]

    except IndexError:
        print('usage: keyanalyzer.py logfile')
        return

    num_results = 25

    # get file contents
    with open(file_name) as f:
        lines = [line.rstrip(' \n') for line in f.readlines()]

    # get substrings, total keys
    substrings = get_substrings(lines, 1, 2)
    total_keys = get_total(substrings)

    print('keyanalyzer.py')
    print('\ttotal_keys : ' + str(int(total_keys)))
    print('\ttype \'h\' for help')

    # query engine
    while True:
        try:
            print
            query       = raw_input('?> ')
            run_query   = False
            query_start = time.time() * 1000

            # help
            if   query[0] == 'h':
                print(help_text)

            # quit
            elif query[0] == 'q':
                return

            # clear
            elif query[0] == 'c':
                print '\n' * 100

            # set: query range
            elif query[0] == 'r':
                try:
                    start, end = [int(x) for x in query[2:].split('-')]

                except ValueError:
                    start = end = int(query[2:])

                finally:
                    end += 1

                substrings = get_substrings(lines, start, end)

            # set: query size
            elif query[0] == 's':
                num_results = int(query.split(' ')[1])

            # query: default
            elif query[0] == 'd':
                condition = False
                run_query = True

            # query: match all strings
            elif query[0] == 'm':
                matches   = query[2:].split()
                condition = lambda key : all(x in key for x in matches)
                run_query = True

            # query: match any strings
            elif query[0] == 'n':
                matches   = query[2:].split()
                condition = lambda key : key in matches
                run_query = True

            # query: filter strings
            elif query[0] == 'f':
                filters   = query[2:].split()
                condition = lambda key : all(x not in key for x in filters)
                run_query = True

            # query: find string
            elif query[0] == 't':
                string    = query[2:]
                condition = lambda key : ''.join(key.split('\t')) == string
                run_query = True

            # run the requested query
            if run_query:
                if condition:
                    query_dict = filter_dict(condition, substrings)
                else:
                    query_dict = substrings

                results = sorted(
                    query_dict.items(),
                    key=operator.itemgetter(1))

                print_substrings(results, num_results, total_keys)

            # show response time
            print(' ' * 72 + '%3.3f ms' % (time.time() * 1000 - query_start))

        except (EOFError, KeyboardInterrupt):
            return

        except (ValueError, IndexError):
            print('\ttype \'h\' for help')


if __name__ == '__main__':
    main()
