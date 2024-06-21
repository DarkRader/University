package cz.cvut.kuznear1.tweenapp

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.kuznear1.tweenapp.model.Tweet
import cz.cvut.kuznear1.tweenapp.ui.screen.ScreenState
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch

class HomeViewModel: ViewModel() {
    private val _tweets: MutableStateFlow<List<Tweet>> = MutableStateFlow(listOf())
    val tweets: StateFlow<List<Tweet>> = _tweets

    private val _screenState = MutableStateFlow(ScreenState.Empty)
    val screenState: StateFlow<ScreenState> = _screenState

    fun addTweet() {
        Log.d("HomeViewModel", "addTweet called")
        _screenState.value = ScreenState.Loading
        Log.d("HomeViewModel", "AddTweet called, tweets size: ${_tweets.value.size}")
        viewModelScope.launch {
            delay(1000)
            val tweet = Tweet()
            _tweets.value += tweet
            _screenState.value = ScreenState.Default
        }
    }
}