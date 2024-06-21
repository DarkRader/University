package cz.cvut.kuznear1.dogapp.features.breed.data.api

import kotlinx.serialization.Serializable

@Serializable
data class ApiBreed(
    val id: String,
    val attributes: Attributes,
) {

    @Serializable
    data class Attributes(
        val name: String,
        val description: String,
    )
}