package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api

import kotlinx.serialization.Serializable

@Serializable
class ApiResponse(
    val success: Boolean,
    val message: String
)