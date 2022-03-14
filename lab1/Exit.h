#pragma once

enum class Exit {
    success,
    fileOpenReadFail,

    fileEOF,

    modelUnininialized,
    modelInitialized,
    modelScaleZero,
    noActionToUndo,
    inputInvalidFilename,
    inputCameraTooClose,
    cmdInvalid,
    noMemory,
    nonZeroInputPtr,
    sizeInvalid,

    strEmpty,
    strUninitialized,
    strInitialized,
    strNoEndl,
    strNAN,

    size
};

inline bool isOk(Exit exitCode) {
    return exitCode == Exit::success;
}
