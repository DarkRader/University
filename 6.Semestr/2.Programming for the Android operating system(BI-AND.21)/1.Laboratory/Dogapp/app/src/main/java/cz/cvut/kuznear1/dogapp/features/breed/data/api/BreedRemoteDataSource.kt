package cz.cvut.kuznear1.dogapp.features.breed.data.api

import cz.cvut.kuznear1.dogapp.features.breed.domain.Breed

class BreedRemoteDataSource(private val apiDescription: BreedApiDescription) {


    suspend fun getBreeds(): List<Breed> {
        return apiDescription.getBreeds().data.map { apiBreed ->
            Breed(
                id = apiBreed.id,
                name = apiBreed.attributes.name,
                description = apiBreed.attributes.description,
            )
        }
    }
}