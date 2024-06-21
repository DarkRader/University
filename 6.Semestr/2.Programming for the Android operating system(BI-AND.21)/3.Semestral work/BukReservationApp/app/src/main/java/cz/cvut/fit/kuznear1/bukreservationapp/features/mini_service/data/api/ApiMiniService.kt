package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api

import kotlinx.serialization.Serializable

@Serializable
data class ApiMiniService(
    val uuid: String,
    val name: String,
    val service_alias: String
)