# TODO
import cs50


def count_letters(text):
    letterlength = 0
    for i in range(0, len(text)):
        if text[i].isalpha():
            letterlength += 1
    return letterlength


def count_words(text):
    wordlength = 0
    for i in range(0, len(text)):
        if text[i] == ' ':
            wordlength += 1
    return wordlength + 1


def count_sentences(text):
    sentencelength = 0
    for i in range(0, len(text)):
        if text[i] in ['.', '!', '?']:
            sentencelength += 1
    return sentencelength


text = cs50.get_string("Write Sample Text Here:")
letterlength = count_letters(text)
wordlength = count_words(text)
sentencelength = count_sentences(text)

L = letterlength / wordlength * 100
S = sentencelength / wordlength * 100

index = 0.0588 * L - 0.296 * S - 15.8

if (index >= 16):
    print("Grade 16+\n")
elif (index < 1):
    print("Before Grade 1 \n")
else:
    grade = round(index)
    print(f"Grade {grade}\n")