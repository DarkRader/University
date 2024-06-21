package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.api

import retrofit2.http.GET
import retrofit2.http.Path
import retrofit2.http.Query

interface CharacterApiDescription {

    @GET("character")
    suspend fun getCharacters(): CharactersResponse

    @GET("character/")
    suspend fun getFilteredCharacters(@Query("name") name: String): CharactersResponse

    @GET("character/{id}")
    suspend fun getCharacter(@Path("id") id: Int): ApiCharacter.Character
}