package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain

data class MiniServicesResult(
    val miniServices: List<MiniService>,
    val isSuccess: Boolean
)

data class MiniServiceResult(
    val miniServices: MiniService?,
    val isSuccess: Boolean
)