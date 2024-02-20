load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def download():
    COMMIT = "dd5b546f4eb5a7893841cbf253456e6f1be0ddc7"
    print("downloading boost {} from omegastar".format(COMMIT))
    git_repository(
        name = "com_github_nelhage_rules_boost",
        remote = "https://github.com/nelhage/rules_boost",
        commit = COMMIT,
    )
