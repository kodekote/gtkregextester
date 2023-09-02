# gtkregextester (GTK Regex Tester)
## A tool to test regular expressions against target strings for Linux operating systems (or any system that supports GTK 3).

### Synposis:
Aside from being useful, this code showcases several poorly-documented features of _GTK 3_
that may be of interest to some. Namely:
1. the API to implement custom drawing (including
geometry management and invoking _libcairo_)
1. how to set attributes on widgets that are ignored by the CSS styler (letter-spacing, for example)
1. which properties are allowed on what widget and how to write an XML UI definition file
1. examples of queueing draw operations on a widget manually to keep all widgets up-to-date

The most interesting take-away is probably this: the `GtkStyleProvider` in the form of a CSS styler works
*very* poorly. For serious applications, using _libpango_ is a must. Also, for anyone who wishes to implement
anything beyond the most basic user interfaces, custom drawing (and associated _libcairo_) is another must.
Therefore, the GTK 3 documentation is as good as useless beyond being a reference for function declarations,
signal declarations, and property lists.

### Usage:
Type a regular expression into the top text widget. The status box will turn green for valid regular expressions (as defined by POSIX)
and red for invalid regular expressions.

Type a target string into the bottom box. All matches, as computed by `regexec`, will be highlighted in a green box with a blue border.
The empty string is never matched.


### TODO:
- Add a list view that allows saving regular expressions of interest. Allow output to a text file.
- Add a Java mode which runs a Java program in daemon mode that tests regular expressions as defined in java.util.regex.
- Write a custom `regcomp`--one that does not allow nonsense regular expressions like "ab+*".

![Screenshot](/gtkregextester.png)
