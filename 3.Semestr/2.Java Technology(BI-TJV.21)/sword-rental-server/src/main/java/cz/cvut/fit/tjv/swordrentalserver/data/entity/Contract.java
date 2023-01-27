package cz.cvut.fit.tjv.swordrentalserver.data.entity;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "contract")
public class Contract implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private long contractId;

    private String date;
    private long price;
    private String event;
    private String deliveryService;

    @ManyToOne
    @OnDelete(action = OnDeleteAction.CASCADE)
    private Person person;

    @OneToOne
    @OnDelete(action = OnDeleteAction.CASCADE)
    private Sword sword;

    public Contract(long contractId, String date, long price, String event, String deliveryService, Person person, Sword sword) {
        this.contractId = contractId;
        this.date = date;
        this.price = price;
        this.event = event;
        this.deliveryService = deliveryService;
        this.person = person;
        this.sword = sword;
    }

    public  Contract() {}

    public long getContractId() {
        return contractId;
    }

    public void setContractId(long contractId) {
        this.contractId = contractId;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public long getPrice() {
        return price;
    }

    public void setPrice(long price) {
        this.price = price;
    }

    public String getEvent() {
        return event;
    }

    public void setEvent(String event) {
        this.event = event;
    }


    public String getDeliveryService() {
        return deliveryService;
    }

    public void setDeliveryService(String deliveryService) {
        this.deliveryService = deliveryService;
    }

    public Person getPerson() {
        return person;
    }

    public void setPerson(Person person) {
        this.person = person;
    }

    public Sword getSword() {
        return sword;
    }

    public void setSword(Sword sword) {
        this.sword = sword;
    }

    //For tests

//    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        Contract contract = (Contract) o;
//        return contractId == contract.contractId && price == contract.price && Objects.equals(date, contract.date) && Objects.equals(event, contract.event) && Objects.equals(deliveryService, contract.deliveryService) && Objects.equals(person, contract.person) && Objects.equals(sword, contract.sword);
//    }
//
//    @Override
//    public int hashCode() {
//        return Objects.hash(contractId, date, price, event, deliveryService, person, sword);
//    }
//
//    @Override
//    public String toString() {
//        return "Contract{" +
//                "contractId=" + contractId +
//                ", date='" + date + '\'' +
//                ", price=" + price +
//                ", event='" + event + '\'' +
//                ", deliveryService='" + deliveryService + '\'' +
//                ", person=" + person +
//                ", sword=" + sword +
//                '}';
//    }
}


