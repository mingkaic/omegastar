load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def download():
    TAG = "v1.13.0"
    print("downloading gtest {} from omegastar".format(TAG))
    git_repository(
        name = "gtest",
        remote = "https://github.com/google/googletest",
        tag = TAG,
    )
