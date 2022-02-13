count_letter = 0
count_word = 1
count_sentence = 0

# Collecting input from user
text = input("Please Enter Text: ")
text_length = len(text)

# Count the number of letters
for i in range(text_length):
    if(text[i].isalpha()):
        count_letter += 1

# Count the number of words
    if (text[i].isspace()):
        count_word += 1

# Count the number of sentences
    if(text[i] == '.' or text[i] == '?' or text[i] == '!'):
        count_sentence += 1

# Calculate Index
calculation = (0.0588 * count_letter / count_word * 100) - (0.296 * count_sentence / count_word * 100) - 15.8

index = round(calculation)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")