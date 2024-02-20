workspace(name = "com_github_mingkaic_omegastar")

# === load local dependencies ===

load("//third_party:all.bzl", omegastar_dl="download")
omegastar_dl()

# === load test dependencies ===

load("//third_party:all.bzl", omegastar_dl_test="download_test")
omegastar_dl_test()

# === boost dependencies ===

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
