#!/usr/bin/python

# keyanalyzer.py
#   Author: Austin Voecks

# example usage:
#   python keyanalyzer.py ~/.keyview.log 50 1-5

import sys, operator, time

help_text = \
    'h         : help'\
    'r int-int : set substring size range'\
    's int     : set number of results'\
    'd         : default query'\
    'm str ... : query, results must match provided input'\
    'f str ... : query, results must not match provided input'\
    't str     : query, results must match provided input exactly'

def get_substrings(lines, range_start, range_end):
    ''' list of strings, int, int -> dict of strings to lists of ints

    fills a dictionary with the frequencies of substrings, where the substrings
    are sizes from @range_start to @range_end. this is completed in one pass
    '''
    substrings = {}
    offsets = xrange(range_start, range_end)

    for line_index in xrange(len(lines)):
        base = '\t'.join(lines[line_index:line_index + range_start])

        for offset in offsets:
            try:
                substrings[base][0] += 1
            except KeyError:
                substrings[base] = [1, offset]

            try:
                base += '\t' + lines[line_index + offset]
            except IndexError:
                pass

    return substrings


def get_total(substrings):
    ''' dict of strings to lists of ints -> float
    '''
    total = 0.0

    for key in substrings:
        if substrings[key][1] == 1:
            total += substrings[key][0]

    return total

def shorthand(substring):
    ''' string -> string
    '''
    out  = ''
    keys = substring.split('\t')
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
        sequence_count = substring[1][0]

        if total_keys:
            ratio = (substring[1][0] / total_keys) * 100
            print("%-50s%-15d%6.2f" % (key_sequence[:50], sequence_count, ratio))

        else:
            print("%-50s%-15d" % (key_sequence[:50], sequence_count))


def filter_dict(condition, dictionary):
    ''' function, dict -> dict
    '''
    out = []
    for key in dictionary:
        if condition(key):
            out.append((key, dictionary[key]))
    return dict(out)


def main():
    ''' string -> IO
    '''
    # agruments
    try:
        file_name = sys.argv[1]
    except IndexError:
        print('usage: keyboard_device top_n range')
        return

    num_results = 25

    # get file contents
    with open(file_name) as f:
        lines = [x.rstrip(' \n') for x in f.readlines()]

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
            query = raw_input('?> ')
            query_start = time.time() * 1000
            run_query = False

            # help
            if query[0] == 'h':
                print(help_text)

            # set: query range
            elif query[0] == 'r':
                try:
                    start, end = [int(x) for x in query[2:].split('-')]
                except ValueError:
                    start = end = int(query[2:])
                end += 1

                substrings = get_substrings(lines, start, end)

            # set: query size
            elif query[0] == 's':
                num_results = int(query.split(' ')[1])

            # query: default
            elif query[0] == 'd':
                condition = False
                run_query = True

            # query: match strings
            elif query[0] == 'm':
                matches = query[2:].split()
                condition = lambda key : all(x in key for x in matches)
                run_query = True

            # query: filter strings
            elif query[0] == 'f':
                filters = query[2:].split()
                condition = lambda key : all(x not in key for x in filters)
                run_query = True

            # query: find string
            elif query[0] == 't':
                string = query[2:]
                condition = lambda key : ''.join(key.split('\t')) == string
                run_query = True

            # run the requested query
            if run_query:
                if condition:
                    query_dict = filter_dict(condition, substrings)
                else:
                    query_dict = substrings

                results = sorted(query_dict.items(), key=operator.itemgetter(1))
                print_substrings(results, num_results, total_keys)

            print(' ' * 72 + '%3.3f ms' % (time.time() * 1000 - query_start))

        except (EOFError, KeyboardInterrupt):
            return

        except (ValueError):
            print('\ttype \'h\' for help')


if __name__ == '__main__':
    main()
