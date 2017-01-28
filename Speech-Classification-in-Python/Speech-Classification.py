# Import Required Packages
import nltk
import random
from nltk.tokenize import TweetTokenizer
from nltk.corpus import stopwords
import string

# Read Test Data
tknzr = TweetTokenizer()
# We have included the different test links for both candidate which you can copy to test_speech file.
h_fp1 = open("test_speech", "rb+")
data = h_fp1.read()
h_fp1.close()
data = data.decode(encoding='UTF-8',errors='strict')
punctuations = set(string.punctuation)

test_words = []
# Tokenize Text Files into set of words For Test Speech
tok_word = tknzr.tokenize(data)
without_punc = [word for word in tok_word if word not in punctuations]
test_filter_words = [word for word in without_punc if word not in stopwords.words('english')]

# Read Trump Data
t_fp = open("Trump.txt", "rb+")
data = t_fp.read()
t_fp.close()
data = data.decode(encoding='UTF-8',errors='strict')
t_speeches = data.split("&&&&&")


# Read Hillary Data
h_fp = open("Hillary.txt", "rb+")
data = h_fp.read()
h_fp.close()
data = data.decode(encoding='UTF-8',errors='strict')
speaches = data.split("&&&&&")
punctuations = set(string.punctuation)

hillary_words = []
trump_words = []
speaches_tagged = []


for s in speaches:
    # Tokenize Text Files into set of words For Hillary Speeches
    tok_word = tknzr.tokenize(s)

    # Remove Punctuations
    without_punc = [word for word in tok_word if word not in punctuations]

    # Remove Stop Words
    filter_words = [word for word in without_punc if word not in stopwords.words('english')]

    # Append Into List of Hillary Words
    hillary_words += [word for word in filter_words]

    # Add the current speech into Tagged Speech Of Hillary for creating Test Data Set
    speaches_tagged.append((filter_words, "Hillary"))


for s in t_speeches:
    # Tokenize Text Files into set of words For Trump Speeches
    tok_word = tknzr.tokenize(s)

    # Remove Punctuations
    without_punc = [word for word in tok_word if word not in punctuations]

    # Remove Stop Words
    filter_words = [word for word in without_punc if word not in stopwords.words('english')]

    # Append Into List of Trump Words
    trump_words += [word for word in filter_words]

    # Add the current speech into Tagged Speech Of Trump for creating Test Data Set
    speaches_tagged.append((filter_words, "Trump"))

# Speeched are shuffled to add random Factor
random.shuffle(speaches_tagged)

# Create List of All Words Trump + Hillary
all_words = ([word for word in hillary_words] + [word for word in trump_words])

# Create List of Frequency Distribution of All Words Trump + Hillary
all_words_freq = nltk.FreqDist(w.lower() for w in all_words)

# Top 2000 words from Frequency Words are taken for consideration
word_features = list(all_words_freq)[:2000]

# This Function takes the Words List and Create a Dictionry of Conditions: contains("each words") = True / False
def document_features(document):
    document_words = set(document)
    features = {}
    for word in word_features:
        features['contains({})'.format(word)] = (word in document_words)
    return features #Returns the Dictionary

# Main Feature Set that is going to be used as source of Naive Bayes Classification.
# For each Tagged Speech we create Feature list with its tag using the  document_features Function
featuresets = [(document_features(d), c) for (d, c) in speaches_tagged]

# Create the Classifier
classifier = nltk.NaiveBayesClassifier.train(featuresets)

# Check Accuracy of Classifier for with  first 5 speeches from feature sets
print("Accuracy: ", nltk.classify.accuracy(classifier, featuresets[:5]))

# Print top Features that are considered for classification
print(classifier.show_most_informative_features(15))

#Print Test Output
print("The Speech in Test_Speech File Belongs to :", classifier.classify(document_features(test_filter_words)))
