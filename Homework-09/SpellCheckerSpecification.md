## Input Format

For the purposes of spell checking, a *word* is a sequence of one or more characters that

* Begins and ends with a letter (i.e., a character for which `isalpha` is true) **and**
* Contains no spaces (i.e., characters for which `isspace` is true).

In the input text, any two consecutive words are separated by a sequence of nonletter characters containing at least one
whitespace character. Although words in the input text may be mixed-case, your program will always convert words to lowercase (using `tolower`) before comparing them against words in the dictionary.  Thus, if your input was `STOP! -- don't "dispatch" C.I.A. under-secretary Jones!`, the words in that input are `stop`, `don't`, `dispatch`, `c.i.a`, `under-secretary`, and `jones`. Dictionary files are a sequence of unique lowercase words separated by whitespace.  Words may occur in dictionary files in any order, without duplication.

## Output Format

Each line in the correction output should consist of the incorrect word followed by a colon (`:`) and zero or more corrections separated by spaces.  There should be exactly one space after the colon (*unless there are no corrections*), and there should be no whitespace at the end of each line.  The following example shows valid output:

```
unix$ ./myspell smalldict.words < error-filled-file.txt
xyzzy:
foo: for
wird: bird gird ward word wild wind wire wiry
```

If a word is misspelled multiple times in the input file, it should only be printed once. If every word in the input is found in the dictionary, `myspell` should produce no output on `cout`, not even an empty line.

## Debugging Command-Line Option

Your `myspell` program must also support a debugging option, whereby the command `./myspell -d ispell.words` reads
the dictionary `ispell.words` and performs spell checking as usual, but also prints information about the data structure used to represent the dictionary.  This information should be printed immediately after the dictionary has been read, before spell checking begins, and sent to `cerr` (**not** `cout`).  This output is required to be in *exactly* the following format:

The code to process the arguments is provided for you, in `myspell.cpp`.


```
n expansions, load factor f, c collisions, longest run l
```

where *n*, *c*, and *l* are integers, and *f* is a floating-point (`double`) number, printed in the default format. This output should end with a newline character (i.e., `endl`). The output corresponds to (or is easily calculated from) statistical information provided by the `HashSet` template class.  For example, `longest run`  refers to the value returned by `maximal`.
