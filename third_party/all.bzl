load("//third_party:repos/boost.bzl", boost_dl="download")
load("//third_party:repos/gtest.bzl", gtest_dl="download")

def validate(dep, excludes, force_includes):
    return dep not in excludes or dep in force_includes

def download(excludes = [], force_includes = []):
    ignores = native.existing_rules().keys() + excludes
    print("downloading omegastar dependencies. ignoring {}".format(ignores))

    if validate("com_github_nelhage_rules_boost", ignores, force_includes):
        boost_dl()

def download_test(excludes = [], force_includes = []):
    ignores = native.existing_rules().keys() + excludes
    print("downloading test omegastar dependencies. ignoring {}".format(ignores))

    if validate("gtest", ignores, force_includes):
        gtest_dl()
