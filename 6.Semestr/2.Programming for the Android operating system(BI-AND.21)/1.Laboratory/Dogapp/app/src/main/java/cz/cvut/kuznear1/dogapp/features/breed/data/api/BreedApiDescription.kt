package cz.cvut.kuznear1.dogapp.features.breed.data.api

import retrofit2.http.GET

interface BreedApiDescription {

    @GET("breeds")
    suspend fun getBreeds(): BreedsResponse
}