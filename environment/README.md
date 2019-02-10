# CS 403
## Designer Programming Language Milestone IV: Environment

The fourth installment of our designer programming language is the Environment, which holds information about which variables are in what scope, and what their values are.<br><br>
The environment has the following capabilities:
- inserting an identifier and value into the most local table: `insert()`
- searching tables from most local to most outer, and returning the value of an identifier: `lookup()`
- setting the value of an identifier: `update()`
- creating an empty environment: `create()`
- extending an environment, while keeping the integrity of current variables and their values: `extend()`
- displaying the local environment; displaying the entire environment: `displayLocal(); display()`
<br><br>

To use this module, a makefile is provided. A `make` or `make environment` command will compile the module, and simply running `environment` will test the environment functions using `env-test.c`, in which all of the aforementioned capabilities are tested; the output will shows that they work as intended.<br><br>
