package cz.cvut.kuznear1.dogapp.features.breed.data

import cz.cvut.kuznear1.dogapp.features.breed.data.api.BreedRemoteDataSource
import cz.cvut.kuznear1.dogapp.features.breed.data.db.BreedLocalDataSource
import cz.cvut.kuznear1.dogapp.features.breed.domain.BreedsResult
import kotlinx.coroutines.flow.first

class BreedRepository(
    private val localDataSource: BreedLocalDataSource,
    private val remoteDataSource: BreedRemoteDataSource,
) {

    suspend fun getBreeds(): BreedsResult {
        return try {
            val breeds = remoteDataSource.getBreeds()
            localDataSource.deleteAll()
            localDataSource.insert(breeds)
            BreedsResult(breeds, isSuccess = true)
        } catch (t: Throwable) {
            BreedsResult(localDataSource.getBreedsStream().first(), isSuccess = false)
        }
    }

    suspend fun getBreed(id: String) = localDataSource.getBreed(id)
}