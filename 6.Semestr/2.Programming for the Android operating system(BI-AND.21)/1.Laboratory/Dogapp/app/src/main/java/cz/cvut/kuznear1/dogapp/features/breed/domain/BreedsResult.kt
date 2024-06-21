package cz.cvut.kuznear1.dogapp.features.breed.domain

data class BreedsResult(
    val breeds: List<Breed>,
    val isSuccess: Boolean,
)