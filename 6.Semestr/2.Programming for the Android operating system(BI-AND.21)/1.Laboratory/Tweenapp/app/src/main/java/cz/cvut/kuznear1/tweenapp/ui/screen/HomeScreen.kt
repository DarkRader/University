package cz.cvut.kuznear1.tweenapp.ui.screen

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AccountCircle
import androidx.compose.material.icons.filled.Add
import androidx.compose.material3.Card
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.sp
import cz.cvut.kuznear1.tweenapp.HomeViewModel
import cz.cvut.kuznear1.tweenapp.R
import cz.cvut.kuznear1.tweenapp.model.Tweet
import cz.cvut.kuznear1.tweenapp.ui.BottomBar
import cz.cvut.kuznear1.tweenapp.ui.theme.paddingLarge
import cz.cvut.kuznear1.tweenapp.ui.theme.paddingMedium


enum class ScreenState {
    Loading,
    Empty,
    Default
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun HomeScreen(viewModel: HomeViewModel = HomeViewModel()) {
    val tweets by viewModel.tweets.collectAsState()
    val screenState by viewModel.screenState.collectAsState()

    Scaffold(
        topBar = {
            CenterAlignedTopAppBar(title =
            { Text(stringResource(R.string.my_wall)) })
        },
        floatingActionButton = {
            FloatingActionButton(onClick = {
                viewModel.addTweet()
            }) {
                Icon(Icons.Default.Add, contentDescription = null)
            }
        },
        bottomBar = { BottomBar() }
    ) {
        when (screenState) {
            ScreenState.Loading -> LoadingScreen(modifier = Modifier.padding(it))
            ScreenState.Empty -> EmptyScreen(modifier = Modifier.padding(it))
            ScreenState.Default -> Column(modifier = Modifier.padding(it)) {
                LazyColumn {
                    items(tweets) {tweet ->
                        TweetCard(tweet = tweet)
                    }

                }
            }
        }
    }
}


@Preview
@Composable
fun TweetCard(modifier: Modifier = Modifier, tweet: Tweet = Tweet()) {
    Card(modifier = Modifier.padding(paddingLarge)) {
        User(name = tweet.name, handle = tweet.handle)
        Text(text = tweet.message)
    }
}

@Preview
@Composable
fun User(name: String = "Bruce Wayne", handle: String = "bruce_wayne") {
    Row(
        modifier = Modifier.fillMaxWidth(),
        horizontalArrangement = Arrangement.Start,
        verticalAlignment = Alignment.CenterVertically
    ) {
        Icon(
            Icons.Default.AccountCircle,
            contentDescription = null
        )
        Spacer(modifier = Modifier.size(paddingMedium))
        Text(
            text = stringResource(R.string.handle, handle),
            fontSize = 20.sp,
            fontWeight = FontWeight.Bold,
            modifier = Modifier.alignByBaseline()
        )
        Spacer(modifier = Modifier.size(paddingMedium))
        Text(
            text = stringResource(R.string.handle, handle),
            fontSize = 14.sp,
            modifier = Modifier.alignByBaseline()
        )
    }
}