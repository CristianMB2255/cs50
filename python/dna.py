import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print(f"Correct usage: python {sys.argv[0]} <individuals> <sequence>")
        return

    # Read database file into a variable
    individuals = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)

        # Read every line into the array
        for row in reader:
            individuals.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence_file:
        sequence = sequence_file.read()

    # Find longest match of each STR in DNA sequence
    str_dict = {}
    for str_name in reader.fieldnames[1:]:
        str_dict[str_name] = longest_match(sequence, str_name)

    # Check database for matching profiles
    corresponding = None
    for individual in individuals:
        for str_name in str_dict:

            # Check each STR values
            if int(individual[str_name]) != str_dict[str_name]:
                break

        # If every STR corresponds, set matching name
        else:
            corresponding = individual["name"]

    if not corresponding:
        print("No match")
        return

    print(corresponding)
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