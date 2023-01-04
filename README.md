# Regex Trie
Inspired by [this video](https://www.youtube.com/watch?v=yju4zwKSriI&t=461s), specifically from timestamp: [42:51](https://www.youtube.com/watch?v=yju4zwKSriI&t=2572s)  

The main idea is to use a [Trie](https://en.wikipedia.org/wiki/Trie) to store a dictionary of words 
and then query the trie to not only search for a word but also perform some pattern matching 
(where * means any ascii character). The trick (as highlighted in the video above)  
is that when you push the word into the dictionary, you also push all valid pattern combinations too.
This means that the setup time would be very long (O(2^(length of string)) for each string) but the time to match a pattern in the dictionary is now O(length of string) time  

For example, if "foo" and "bar" were added to the dictionary&mdash;using the `add_regex` function, of course. Then,
```c
find_word("foo");
find_word("*oo");
find_word("***");
find_word("ba*");
```
will all return true

PS: There are a some weird tricks used in this project. 
This is partly because this is my first time working with tries and also because 
I might have payed a bit too much attention on the time and space complexity of the code
