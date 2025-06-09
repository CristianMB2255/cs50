from cs50 import get_string


# Calculate the number of words
def count_words(text):

    wordCount = 1
    previous = ' '
    length = len(text)

    for i in range(length):

        # Check if character is a space
        char = text[i]
        if char == ' ' and previous != ' ':
            wordCount += 1

        # Store last character for next iteration
        previous = char

    return wordCount


# Count the number of letters per 100 words
def count_letters(text, words):

    lettersCount = 0
    length = len(text)

    for i in range(length):

        # Check if char is a letter
        if text[i].isalpha():
            lettersCount += 1

    # Calculate the average per 100 words
    average = lettersCount / words * 100

    return average


# Count the number of sentences per 100 words
def count_sentences(text, words):

    punctuations = ['.', '?', '!']
    length = len(text)
    previous = ''
    sentencesCount = 0

    for i in range(length):

        # Check if character is a punctuation
        char = text[i]
        if char in punctuations and previous not in punctuations:
            sentencesCount += 1

        # Store last character for next iteration
        previous = char

    # Calculate the average per 100 words
    average = sentencesCount / words * 100

    return average


# Calculate the Coleman-Liau index
def coleman_index(letters, sentences):

    # Index = 0.0588 * L - 0.296 * S - 15.8
    level = (0.0588 * letters) - (0.296 * sentences) - 15.8

    return round(level)


# Get text
text = get_string("Text: ")

# Calculate text metrics
words = count_words(text)
letters = count_letters(text, words)
sentences = count_sentences(text, words)

# Colemn-Liau index
level = coleman_index(letters, sentences)

# Print level
if level < 1:
    print("Before Grade 1")
elif level > 16:
    print("Grade 16+")
else:
    print(f"Grade {level}")
