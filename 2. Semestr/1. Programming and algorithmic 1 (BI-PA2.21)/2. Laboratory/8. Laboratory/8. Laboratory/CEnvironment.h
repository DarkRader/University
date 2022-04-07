/**
 * @author Jan Matoušek
 * @copybrief Whoever copies the file, should at least understand it
 */

#pragma once

/**
 * Information about environment conditions
 */
struct CEnvironment {
    int tempCelsius; ///< Environment temperature in degrees of Celsius
    bool hasOxygen; ///< Whether there is oxygen present in the environment
};
