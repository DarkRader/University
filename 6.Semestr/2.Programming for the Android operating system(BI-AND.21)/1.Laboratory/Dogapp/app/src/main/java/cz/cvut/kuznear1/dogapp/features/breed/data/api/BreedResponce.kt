package cz.cvut.kuznear1.dogapp.features.breed.data.api

import kotlinx.serialization.Serializable

@Serializable
data class BreedsResponse(val data: List<ApiBreed>)