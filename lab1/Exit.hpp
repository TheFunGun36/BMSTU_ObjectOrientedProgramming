#pragma once

enum class Exit {
    success,
    fileOpenReadFail,
    fileOpenWriteFail,

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

    actionUnknown,

    size
};

inline bool isOk(Exit exitCode) {
    return exitCode == Exit::success;
}
