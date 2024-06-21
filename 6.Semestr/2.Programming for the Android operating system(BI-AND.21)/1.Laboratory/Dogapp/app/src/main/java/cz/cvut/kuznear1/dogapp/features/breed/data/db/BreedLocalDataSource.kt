package cz.cvut.kuznear1.dogapp.features.breed.data.db

import cz.cvut.kuznear1.dogapp.features.breed.domain.Breed
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

class BreedLocalDataSource(private val breedDao: BreedDao) {

    fun getBreedsStream(): Flow<List<Breed>> = breedDao.getBreedsStream().map { dbBreeds ->
        dbBreeds.map { it.toDomain() }
    }

    private fun DbBreed.toDomain(): Breed {
        return Breed(
            id = id,
            name = name,
            description = description,
        )
    }

    suspend fun getBreed(id: String): Breed? = breedDao.getBreed(id)?.toDomain()

    suspend fun insert(breeds: List<Breed>) {
        val dbBreeds = breeds.map { breed ->
            DbBreed(
                id = breed.id,
                name = breed.name,
                description = breed.description,
            )
        }
        breedDao.insert(dbBreeds)
    }

    suspend fun deleteAll() {
        breedDao.deleteAll()
    }
}