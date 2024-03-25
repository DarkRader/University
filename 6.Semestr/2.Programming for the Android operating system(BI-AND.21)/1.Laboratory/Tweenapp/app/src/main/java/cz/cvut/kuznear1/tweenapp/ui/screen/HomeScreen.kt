package cz.cvut.kuznear1.tweenapp.ui.screen

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
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
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import cz.cvut.kuznear1.tweenapp.HomeViewModel
import cz.cvut.kuznear1.tweenapp.R
import cz.cvut.kuznear1.tweenapp.model.Tweet
import cz.cvut.kuznear1.tweenapp.ui.BottomBar
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import java.lang.reflect.Modifier

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun HomeScreen(viewModel: HomeViewModel = HomeViewModel()) {
    val tweets by viewModel.tweets.collectAsState()
    val coroutineScope = rememberCoroutineScope()

    Scaffold {
        topBar = {
            CenterAlignedTopAppBar(title =
            {Text(stringResource(R.string.my_wall)) })
        },
        floatingActionButton = {
            FloatingActionButton(onClick = {
                coroutineScope.launch(Dispatchers.Main) {
                    viewModel.addTweet()
                }
            }) {
                Icon(Icons.Default.Add, contentDescription = null)
            }
        },
        bottomBar = { BottomBar() }
        ) {
//            when (screenState) {
//                ScreenState.Loading -> LoadingScreen(modifier = Modifier)
//                ScreenState.Empty -> Empty()
//                ScreenState.Default -> Default()
//            }
            Column(modifier = Modifier.padding(it)) {
                LazyColumn {
                    items(tweets) {
                        TweetCard(tweet)
                    }
                }
            }
    }
    }
}

@Preview
@Composable
fun TweetCard(tweet: Tweet) {
    Card(modifier = Modifier.padding(16.dp)) {
        User()
        Text(text = tweet.message)
    }
}

@Preview
@Composable
fun User(name: String = "Bruce Wayne", handle: String = "bruice_wayne") {
    Row(
        modifier = Modifier.fillMaxWidth(),
        horizontalArrangement = Arrangement.Start,

    ) {
        Icon(
            Icons.Default.AccountCircle,
            contentDescription = null
        )
        Spacer(modifier = Modifier.size(8.dp))
        Text(
            text = name,
            fontSize = 20.sp,
            fontWeight = FontWeight.Bold,
            modifier = Modifier.alignByBaseline()
        )
    }
}