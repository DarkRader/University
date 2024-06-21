package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain

import kotlinx.serialization.Serializable

@Serializable
data class CreateEvent(
    val start_datetime: String,
    val end_datetime: String,
    val purpose: String,
    val guests: Int,
    val reservation_type: String,
    val email: String,
    val additional_services: List<String>?,
    val username: String
)

fun CreateDefaultEvent(): CreateEvent {
    return CreateEvent(
        start_datetime = "2024-06-05T13:59",
        end_datetime = "2024-06-05T17:00",
        purpose = "",
        guests = 0,
        reservation_type = "",
        email = "",
        additional_services = null,
        username = "",
    )
}