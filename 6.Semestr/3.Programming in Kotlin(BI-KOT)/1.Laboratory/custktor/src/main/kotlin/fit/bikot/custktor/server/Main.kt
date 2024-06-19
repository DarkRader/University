package fit.bikot.custktor.fit.bikot.custktor.server

import fit.bikot.ratio.Cust
import fit.bikot.ratio.custFacade
import io.ktor.http.*
import io.ktor.serialization.gson.*
import io.ktor.server.application.*
import io.ktor.server.engine.*
import io.ktor.server.netty.*
import io.ktor.server.plugins.contentnegotiation.*
import io.ktor.server.response.*
import io.ktor.server.routing.*

fun main() {
    embeddedServer(
        Netty, port = 8080,
        module = Application::mainModule
    ).start(wait = true)
}

fun Application.mainModule() {
    this.install(ContentNegotiation) {
        gson { }
    }
    routing {
        get("/") {
            call.respond(custFacade.all)
        }
        get("/{id}") {
            val id = call.parameters["id"]!!.toLong()
            val cust = custFacade.get(id)
            if (cust == null)
                call.respond(HttpStatusCode.NotFound)
            else call.respond<Cust>(cust)
        }
    }
}