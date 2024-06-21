package cz.cvut.kuznear1.batmanapp

import android.util.Log
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.outlined.Send
import androidx.compose.material.icons.rounded.Add
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.Icon
import androidx.compose.material3.SuggestionChip
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import cz.cvut.kuznear1.batmanapp.ui.theme.Yellow

@Composable
fun ProfileScreen() {
    Box(modifier = Modifier.fillMaxSize()) {
        Column(modifier = Modifier
            .fillMaxSize()
            .padding(16.dp)) {
            Header()
            Statistics()
            Skills()
            SendSignal() {}
        }
        AddFriend(
            modifier = Modifier
                .align(Alignment.BottomEnd)
                .padding(16.dp)
        ) {
            Log.d("Batman app", "Adding Batman friends")
        }
    }
}

@Composable
fun AddFriend(modifier: Modifier, onClick: () -> Unit) {
    FloatingActionButton(
        modifier = modifier,
        onClick = onClick,
        containerColor = Yellow
    ) {
        Icon(imageVector = Icons.Rounded.Add,
            contentDescription = "",
            )
    }
}

@Composable
fun SendSignal(onClick: () -> Unit) {
    Button(
        modifier = Modifier.fillMaxWidth(),
        colors = ButtonDefaults.buttonColors(
            containerColor = Color.Black
        ),
        onClick = onClick
    ) {
        Text(text = "Send signal")
        Icon(
            modifier = Modifier.padding(start = 12.dp),
            imageVector = Icons.Outlined.Send,
            tint = Color.White,
            contentDescription = "Send icon")
    }
}

@Composable
fun Skills() {
    val skills = listOf("Dark", "Perfect", "Dangerous", "Vengeful", "Rich")

    LazyRow(modifier = Modifier
        .background(Color.White)
    ) {
        items(skills) { skill ->
            SkillChip(title = skill)
        }
    }

}

@Composable
fun SkillChip(title: String) {
    SuggestionChip(
        modifier = Modifier.padding(4.dp),
        onClick = { },
        label = { Text(text = title)
        })
}

@Composable
fun Statistics() {
    Card(
        colors = CardDefaults.cardColors(
            containerColor = Color(0xFFEFF0F1)
        )
    ) {
        Row(modifier = Modifier.fillMaxWidth()) {
            StatItem(Modifier.weight(1f), "Followers", 3)
            StatItem(Modifier.weight(1f), "Friends", 28)
            StatItem(Modifier.weight(1f), "Project", 2)
        }
    }
}

@Composable
fun StatItem(modifier: Modifier, title: String, value:Int) {
    Column(
        modifier = modifier.padding(16.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "$value", fontWeight = FontWeight.ExtraBold)
        Text(text = title)
    }
}

@Composable
fun Header() {
    Row(modifier = Modifier
        .fillMaxWidth()
        .height(100.dp)
        .background(Color.White)
    ) {
        Image(
            modifier = Modifier
                .size(100.dp)
                .padding(8.dp)
                .clip(CircleShape),
            painter = painterResource (id = R.drawable.batman),
            contentDescription = "ProfileImage",
            contentScale = ContentScale.Crop,
        )
        Column(
            modifier = Modifier
                .fillMaxHeight()
                .padding(start = 8.dp),
            verticalArrangement = Arrangement.Center
        ) {
            Text(
                text = stringResource(id = R.string.name),
                fontWeight = FontWeight.Bold,
                fontSize = 20.sp
            )
            Text(text = stringResource(id = R.string.description))
        }
    }
}

@Composable
@Preview
fun PreviewProfileScreen() {
    ProfileScreen()
}