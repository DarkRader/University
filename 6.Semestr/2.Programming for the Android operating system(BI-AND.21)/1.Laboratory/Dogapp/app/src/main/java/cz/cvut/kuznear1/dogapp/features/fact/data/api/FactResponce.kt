package cz.cvut.kuznear1.dogapp.features.fact.data.api

import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable

@Serializable
data class FactsResponse(val data: List<FactData>) {

    @Serializable
    data class FactData(val attributes: Attributes)

    @Serializable
    data class Attributes(@SerialName("body") val fact: String)
}