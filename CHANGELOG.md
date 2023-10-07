# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [v2.0.1] - 2023-10-07

### Removed

- Support for CMake versions older than 3.13.
  - Debian Buster and RHEL7 /w EPEL/SCL should work.
  - CMake 3.7 was supported for Debian Stretch, which is EOL since

### Added

- CPack generator for RPM now enabled if rpmbuild is found.
- `CHANGELOG.md`, `.markdownlint.json`
- `bootstrap.sh` and `bootstrap.cmd`.

### Changed

- Allow `-std=c++23`.
- CPack generator for DEB only enabled if `dpkg` is found.
- No longer set default visiblity for gcc/clang exports.

### Fixed

- Unit tests building with a different standard than the library.
- -Wexpansion-to-defined under clang13.
- Debian packages missing some fields.

## [v2.0.0] - 2021-02-21

### Added

- Code from SxE at commit c5c2112d81a9467842b5db89a4dcf0915139288a.
- Standins for SxE api an stdtypedef headers.
- find_package() support.
- Unit tests.
- New classes:
  - LogSquelch
  - TextLogSink
  - StandardErrorLogSink
  - StandardOutputLogSink
- LogSinks can now be renamed.

### Changed

- LogSink: some variables that were protected are now private.
- Autovivification of StandardOutputLogSink as the default log sink if there are
no log sinks.
- Log::wtf() can now be configured to call terminate regardless of NDEBUG.

### Fixed

- LogSink::translate() missing an entry for verbose level.
- Misc warnings under MSVC.
