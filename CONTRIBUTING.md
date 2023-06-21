# Contribution Guidelines

Help wanted! We'd love your contributions to `Interpol`. Please review the following guidelines before contributing. Also, feel free to propose changes to these guidelines by updating this file and submitting a pull request.

## Have a question?

You can check our tg (@grafvontee and @kr1stt) and ask us!

## Found a bug?
                            
You can use [issues](../../issues) to report bugs. Provide all the requested information, otherwise your issue could be closed. Please also feel free to submit a Pull Request with a fix for the bug! For sensitive security-related issues, please report via telegram!

Consider checking [Bug Template](.github/ISSUE_TEMPLATE/bug_report.md) before reporting.

## Have a Feature Request?

All feature requests should start with [submitting an issue](../../issues/new) documenting the user story and acceptance criteria. Provide all the requested information, otherwise your issue could be closed. Again, feel free to submit a `Pull Request` with a proposed implementation of the feature. 

## Ready to contribute

### Create an issue

Before submitting a [new issue](../../issues/new), please search the 
[issues](../../issues) to make sure there isn't a similar issue doesn't already exist. Assuming no existing issues exist, please ensure you include the following bits of information when submitting the issue to ensure we can quickly reproduce your issue:

* Version used
* Platform (Linux, macOS, Windows)
* The complete command that was executed
* Any output from the command
* Details of the expected results and how they differed from the actual results
* Inform the related specifications that documents and details the expected behavior.

We may have additional questions and will communicate through the GitHub issue, so please respond back to our questions to help reproduce and resolve the issue as quickly as possible.
### How to submit Pull Requests

1. Fork this repo
2. Clone your fork and create a new branch: `git clone https://github.com/GrafVonTee/Interpol.git -b name_for_new_branch`.
3. Make changes and test
4. Publish the changes to your fork
5. Submit a Pull Request with comprehensive description of changes
6. Pull Request must target `develop` branch
7. For a Pull Request to be merged:
   * CI workflow must succeed
   * A project member must review and approve it
   
The reviewer may have additional questions and will communicate through conversations in the GitHub PR, so please respond back to our questions or changes requested during review.

### Dependencies and versions:
Keep in mind to check [Security Policy](SECURITY.md) for our future work!

### <a name="style"></a> Styleguide

When submitting code, please make every effort to follow existing conventions and style in order to keep the code as readable as possible.  Here are a few points to keep in mind:

* p_camelCase, where p: 
  - c=const
  - m=member_field
  - g=global
  - For locals it isn't necessary


* Functions:
```
  returned_value FunctionName(functionArgs, ...) {
        // functions body
  }
```
* Using for new type:
```using new_type_t = another_type;```


* Structs / Classes:
```
struct NewStruct {
    new_t myCumIsVeryHot;
    // no functions inside
}

class NewClass {
    new_t myInnerVar;
    // functions are there
}
```

* File names:

```src/your_part_dir/mySourceCode.cpp```

```include/myHeader.h```


* Enums:
```
enum class MyNewEnum {
    OH_MY_GOD,
    WHAT_IS_THE_ERROR,
}
```

* Namespaces:
```
namespace MyCumCollection {
    // cum collection
}
```
### License

By contributing your code, you agree to license your contribution under the terms of the [MIT License](LICENSE). All files are released with the MIT License.
