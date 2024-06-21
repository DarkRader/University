package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain

import kotlinx.serialization.Serializable

@Serializable
data class MiniServiceRequest(
    val name: String,
    val service_alias: String
)