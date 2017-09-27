# Summarizer

A naive implementation of a tl;dr bot.
To use : "./summarizer [file]"

What it does :
     - Split .txt into sentences
     - Set a score to each word, ignoring case
     - Determine a minimum score, at the moment : [TotalScore/Nb_Sentences]*1.75
     - Display those score and the sentences above the minimum

ToBeDone :
     - Either a better split or an implementation of an existing one
     - Ignore certains word that have no uses
     - Calculate sentences score base on number of word to prevent the display of only long sentences.
     - Idk, just ask ?