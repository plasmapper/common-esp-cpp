# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
- Virtual destructors to Lockable and EventHandler.

### Changed
- Lockable and EventHandler to be non-copyable.

### Fixed
- StreamServer task not being stopped before the derived object is destroyed.
- LockGuard multiple object constructor parameter documentation.

## [2.0.1] - 2026-08-19
### Fixed
- Invalid iterator use in Event::Generate.

## [2.0.0] - 2026-08-14
### Added
- Write operation timeout to Stream (breaking change: adds GetWriteTimeout/SetWriteTimeout pure virtual methods, requiring all Stream implementations to be updated).

## [1.3.1] - 2026-08-11
### Fixed
- Invalid iterator use in Event::RemoveHandler.

## [1.3.0] - 2026-08-07
### Added
- ESP-IDF v6.0 support.

## [1.2.3] - 2026-08-04
### Changed
- Simplified mutex, stream server and buffer lock timeout handling.

### Fixed
- Event handler memory leak.
- Missing lock in stream read buffer flushing.
- Unsynchronized stream server task state flags.
- Silent buffer allocation failure.
- Stream server task stream reference.

## [1.2.2] - 2024-09-10
### Changed
- Hardware interface and server name access mutex.

## [1.2.1] - 2024-08-29
### Fixed
- Missing pl_stream_server include.

## [1.2.0] - 2024-08-29
### Added
- Stream server class.

## [1.1.0] - 2024-08-26
### Added
- Multilock lockguard.

## [1.0.0] - 2024-06-11
Initial release.