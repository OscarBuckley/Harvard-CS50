import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Wrong command format")

    # TODO: Read database file into a variable
    dnadata = []
    with open(sys.argv[1], 'r')as datafile:
        # read to dictionary
        data = csv.DictReader(datafile, delimiter=',')
        # go through any value whose key is not name and convert from str to int
        for i in data:
            for key, value in i.items():
                if key != "name":
                    i[key] = int(value)
            dnadata.append(i)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r')as text:
        dnastring = text.read()

    # TODO: Find longest match of each STR in DNA sequence
    # used to store substring count data. should be dictionary
    results = {}
    # list of substrings
    substrings = list(dnadata[0].keys())[1:]

    # for each substring that needs to be searched
    for i in substrings:
        # use longest match function
        match = longest_match(str(dnastring), str(i))
        # store data into results as dictionary
        results[i] = match

    # TODO: Check database for matching profiles
    # check each person
    for person in dnadata:
        # check each substring
        match = False
        for substring in substrings:
            # break and set match to false if not match.
            if person[substring] == results[substring]:
                match = True
            else:
                match = False
                break
        # if still true after loop then print name and exit
        if match == True:
            print(person["name"])
            sys.exit()

    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
