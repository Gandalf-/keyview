#!/usr/bin/python

# example: python grams.py ~/.keyview.log 2-4 | ratio 20

import sys, operator

def get_grams(grams, lines, start, end):
    ''' list of lists of strings, list of strings, int -> none
    '''
    for i in xrange(len(lines)):
        for n in xrange(start, end):
            try:
                gram = '\t'.join(lines[i:i+n])

                try:
                    grams[gram][0] += 1
                except KeyError:
                    grams[gram] = [1, n]

            except IndexError:
                pass

def main():
    ''' string, int -> none
    '''
    # agruments
    try:
        file_name = sys.argv[1]
        number    = int(sys.argv[2])
        gram_size = sys.argv[3]
    except IndexError:
        print 'usage: keyboard_device top_n range'
        sys.exit(1)

    # given a range or single value?
    try:
        start, end = [int(x) for x in gram_size.split('-')]
    except ValueError:
        start = end = int(gram_size)
    end += 1

    # get file contents
    with open(file_name) as f:
        lines = [x.rstrip(' \n') for x in f.readlines()]

    # get grams of requested sizes
    grams = {}
    get_grams(grams, lines, start, end)

    # sort grams by occurance
    sorted_grams = sorted(grams.items(), key=operator.itemgetter(1))

    # get total key count
    total = 0.0
    for key in grams:
        if grams[key][1] == 1:
            total += grams[key][0]

    # output
    for gram in sorted_grams[-number:][::-1]:

        key_sequence = gram[0].replace('\t', ' ')
        sequence_count = gram[1][0]

        if total:
            ratio = (gram[1][0] / total) * 100
            print "%-40s%-15d%6.2f" % (key_sequence, sequence_count, ratio)

        else:
            print "%-40s%-15d" % (key_sequence, sequence_count)

    print
    print 'total keys: ', int(total)

if __name__ == '__main__':
    main()
