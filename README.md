Qt support only the static features of SVG 1.2 Tiny: https://www.w3.org/TR/SVGMobile12/
But desing programs like Illustrator creates SVG using all of its features.

The one of the key differences is CSS support: SVG Tiny doesn't support styles, it requires to set up style for each element separately.
So this small program transforms SVG with CSS to SVG with styles in individual elements.

INPUT:
Folder that contains one or more SVG files.

OUTPUT:
New files in given folder, with "_tiny" postfix after names.

TODO list:
* Add sanity checks. Now, if input contains something unusual, program will crash. It should ignore such input, show warning message and go further.
* Make something with separating string by separator. std::string doesn't provide standard method for this so this is done in while() cycles in different places which is ugly.
* Cross-platform support. Now it works only on Windows because of OS-specific work with filesystem. It can be changed by using boost::filesystem or C++17 with its std::filesystem.