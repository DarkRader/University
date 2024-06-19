package fit.bikot.custui

import fit.bikot.ratio.Cust
import fit.bikot.ratio.custFacade
import javafx.collections.ObservableList
import tornadofx.View
import tornadofx.asObservable
import tornadofx.readonlyColumn
import tornadofx.tableview

class CustView : View() {
    val custData: ObservableList<Cust> = custFacade.all.toMutableList().asObservable()
    override val root =
        tableview(custData) {
            readonlyColumn("Id", Cust::id)
            readonlyColumn("Name",Cust::name)
        }
    }

