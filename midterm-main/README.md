# CSE 109 - Systems Software - Spring 2022 - Midterm

Due by: 3/11/2022 by EOD

## Ethics Contract

**FIRST**: Please read the following carefully:

- I have not received, I have not given, nor will I give or receive, any assistance to another student taking this exam, including discussing the exam with students in another section of the course. Do not discuss the exam after you are finished until final grades are submitted.
- If I use any resources (including text books and online references and websites), I will cite them in my assignment.
- I will not ask question about how to debug my exam code on Piazza or any other platform.
- I will not plagiarize someone else's work and turn it in as my own. If I use someone else's work in this exam, I will cite that work. Failure to cite work I used is plagiarism.
- I understand that acts of academic dishonesty may be penalized to the full extent allowed by the [Lehigh University Code of Conduct][0], including receiving a failing grade for the course. I recognize that I am responsible for understanding the provisions of the Lehigh University Code of Conduct as they relate to this academic exercise.

If you agree with the above, type your full name in the following space along with the date. Your exam **will not be graded** without this assent. When you are done, **make your first commit with the commit message: `I, <your full name here>, agree to the ethics contract`.**

Write your name and date between the lines below

---------------------------------------------
I, Zach Frain, agree to the ethics contract
---------------------------------------------

## Instructions 

**Read thoroughly before starting your exam:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Exam Prelude

There are a number of questions in this exam divided into two parts. Each question is weighted equally. This exam will test your ability to independently:

- Organize a programming project
- Use the basics of the C progamming language including structs and pointers
- Allocate memory on the heap and use it in a way that does not cause memory leaks
- Implement a library and use that library in an executable
- Write and use Makefiles to automate the build process

In Part 1 you're going to implement the `ls` program which lists directories and files in a target folder.

This repository is blank except for this README file. It's your job to create this program from scratch. You are going to lay out the directory structure, create a Makefile, create a header file, create library source files, implement your executtable, and then finally provide a video that shows it working. You can use any libraries and functions you like to accomplish this.

Part 2 is the oral portion of the exam. I will ask you to pick a couple functions in your program and to record an explanation of your work along with your screen. For more info, see Part 2. **You will not be able to pass this exam without doing this portion.**

### Commit Policy

I'm going to divide the project into discrete "questions", and you must make at least one commit per question. This is how I will know you are not just copying and pasting an entire solution from the internet. I will be able to see how much time you spend on each question based on your commit times. Red flags are raised when certain patterns of behavior indicating cheating are exhibited by your commit activity. 

You can do the questions in any order, and you can go back to questions for which you have already made a commit, but I want you to have at least one commit per question. The commit message for each question should be "QUESTION N" where N is the number of the question.

### Resource Usage Policy

You are free to use any resource for this exam. This includes books, notes, lecture videos, documentation, the internet, Stack Overflow, etc. The only course resources off limits are me and your TAs. I am free to answer clarifying questions, but that's it. I can't help you debug or provide any technical support (this includes support with git. Knowing how to use git is part of this exam.)

If you use any resources from the internet or anywhere else, **YOU HAVE TO CITE THEM** in your exam. Failure to cite resources you used may lead to failure of the exam. This includes the wiki article and videos I posted above. If you use them, cite them every time you use them. See the Works Cited section at the bottom for more deails on how to cite your work in this document using Markdown.

## ls

```
LS(1)                                                                                                                                               User Commands                                                                                                                                              LS(1)

NAME
       ls - list directory contents

SYNOPSIS
       ls [OPTION]... [FILE]...

DESCRIPTION
       List information about the FILEs (the current directory by default).  Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

       Mandatory arguments to long options are mandatory for short options too.

       -a, --all
              do not ignore entries starting with .

       -l     use a long listing format

       --help display this help and exit

       --version
              output version information and exit

   Exit status:
       0      if OK,

       1      if any problems

AUTHOR
       Written by Richard M. Stallman and David MacKenzie.

REPORTING BUGS
       GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
       Report ls translation bugs to <https://translationproject.org/team/>

COPYRIGHT
       Copyright © 2018 Free Software Foundation, Inc.  License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent permitted by law.

SEE ALSO
       Full documentation at: <https://www.gnu.org/software/coreutils/ls>
       or available locally via: info '(coreutils) ls invocation'

GNU coreutils 8.30
```


## Part 1

### Question 1

Lay out your directory structure. Create a `src` directory, an `include` directory, and a blank `Makefile` in the project root. 

- Inside the `src` directory create a `bin` directory. 
- Inside the `src/bin` directory create `main.c`.
- Inside the `src` directory create `lib.c`.
- Inside the `include` directory, create `myls.h`

### Question 2

Implement the Makefile to build your project. It will be a little different than the homework so pay attention to these instructions. Your Makefile should have at least the following directives:

- `static` will generate a static library (libmyls.a) and put it in `build/lib`.
- `shared` will generate a shared library (libmyls.so) and put it in `build/lib` (Remember this [reading][2]).
- `bin` will generate an executable from `main.c` called `main`, which statically links to `libmyls.a` (it should make that as well if it doesn't exist). Put the executable in `build/bin` and the library in `build/lib`. Put object files in `build/objects`.
- `all` will build the static and shared libraries as well as `main`.
- `clean` will clean the project of all build directories and artifacts (*.so *.a *.o main)
- `install` will move the shared library to `/usr/lib`.

### Question 3

In `lib.c`, write a routine that reads a target directory and lists the files and folders in that directory to the screen. You may want to use https://www.man7.org/linux/man-pages/man0/dirent.h.0p.html

You have wide latitude on this part in terms of the functions that you decide implement.

### Question 4

Stub out any function signatures for your ls program in `myls.h`

You can add any other function arguments you see fit to make your functions work. You can add any other functions you want as well.

### Question 5

Handle the `-a` and `--all` flags

### Question 6

Handle the `-l` flag.

Display number of files and folders listed (before the list).

List files/folders in a column, one file/folder per row.

List the name of the item, as well as one other piece of info. e.g.

- date created
- owner
- size
- permission string

Before you list the items, print the number of items to be listed.

### Question 7

Handle the `--help` flag.

- describe usage
- brief description of program
- describe all flags and their usage
- describe output values

### Question 8

Handle the `--version` flag.

Print: "[your name] v.0.0.1"

### Question 9

Prints and formats the output as the real ls program does.

## Part 2

This is the oral portion of the exam. You will record an explanation (min 5 mins.) for the myls program demonstrating its usage and showing how you implemented it. You don't have to show your face but you do have to record your voice.

If you didn't finish the exam in is entirety, explain how you attempted to solve it and where you got stuck. This will get you at least some points. 

You can use Zoom to do this, [here is a link][3] to some instructions. You don't have to record your face, only your voice and the screen. Go through the answer and explain how you arrived there. Your goal with this question is to convince me you know what you are talking about, so I want you to do this without reading a script or written answer. Just go through line by line and explain what the program does. When you are done, upload your recording to your Lehigh Drive and add a link below. **IMPORTANT: Make sure you give me permission to view the file**.

Recording Link(s): https://drive.google.com/file/d/1UFiBDRcHyQLafEoh9Ku5rhPwyfAmNPkw/view?usp=sharing

New Link:          https://drive.google.com/file/d/1UFiBDRcHyQLafEoh9Ku5rhPwyfAmNPkw/view?usp=sharing

## Works Cited

Include a list of websites and resources you used to complete this exam. Make a numbered list, and at the place where you used this resource cite it using [reference style links in Markdown][1] (See this Readme's source for an example. It's invisible in the rendered document, but there are a number of links below this paragraph).

[0]: https://studentaffairs.lehigh.edu/content/code-conduct
[1]: https://www.markdownguide.org/basic-syntax#reference-style-links
[2]: http://crasseux.com/books/ctutorial/Building-a-library.html#Building%20a%20library
[3]: https://support.zoom.us/hc/en-us/articles/201362473-Local-recording
