# CSE109 - Systems Software - Homework 1

**Due Date**: 1/31/2022 EOD

## Preliminaries

1. Sign into your newly created Lehigh Gitlab account. Your username is the first 6 characters of your Lehigh e-mail address. For example, my e-mail address is `cim310@lehigh.edu`, so my gitlab username would be `cim310`. You should have received an e-mail with your login information already. If not, DM me.

2. Choose an avatar image for your Gitlab account. This doesn't have to be a picture of yourself, but that's not a bad choice. Whatever it is, make sure it's appropriate for a classroom setting. Use this same avatar on Slack as well.

3. Create a gew Gitlab Group - [Instructions](https://docs.gitlab.com/ee/user/group/)
  - The group name is particular. It needs to be of the form: `<<your-user-name>>-cse109`. If your username is `abc123`, your group would be named `abc123-cse109`. 
  - It's important to get this right, because some of the course tools will assume this to be the case. **If your name deviates from what I've indicated above, the course tools will not be able to find your account and you will not get a grade for your assignments**.
  - Make sure your group's visibility is set to **Private**. This is to make sure no other student can see your work.

## Instructions

The purpose of this assignment is to familiarize yourself with the homework submission process. Every homework, quiz, and exam will be hosted in a repository located at:

```
http://gitlab.cse.lehigh.edu/cse109/spring-2022/assignments/<assignment-name>
```

Homeworks, quizzes, and exams may require you to write code that passes a number of tests to get full credit. For information on the testing framework refer to the documentation [here](https://docs.gitlab.com/ee/ci/).

The process of accepting and submitting on assignments will proceed as follows:

1. Fork the relevant repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)

2. Clone your newly forked repository to your computer. Your repository should be hosted at 
```
https://gitlab.cse.lehigh.edu/<your lehigh e-mail id>-cse109/<assignment name>
```
It is very important your projects are hosted at this specific address, as the tools I've writted to adminitrate this course assume this address. If you fork an assignment into the wrong namespace, you can easily move it. [Instructions](https://docs.gitlab.com/ee/user/project/settings/#transferring-an-existing-project-into-another-namespace) 


You can use the following git command with the appropriate values substituted to customize it for your :
```
git clone https://gitlab.cse.lehigh.edu/<your lehigh e-mail id>-cse109/<assignment name>
```
[Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 

Here's an example command customized for my group:

```
git clone https://gitlab.cse.lehigh.edu/cim310-cse109/homework-1
```

You would have to change the `cim310` user in this command to your own user id before it can work for you.

3. Navigate to the newly cloned directory. Fix the code in `main.c` by adding a semicolon at the end of line 4. Save the file after you've added the missing character.

4. Commit and push this change to the Lehigh Gitlab instance. Follow the instructions [here](https://githowto.com/staging_and_committing) (read sections 6, 7 and 8) about staging and committing changes.
