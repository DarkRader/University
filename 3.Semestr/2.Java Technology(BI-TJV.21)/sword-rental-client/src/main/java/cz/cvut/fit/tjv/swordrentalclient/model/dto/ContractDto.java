package cz.cvut.fit.tjv.swordrentalclient.model.dto;


import com.fasterxml.jackson.annotation.JsonFormat;
import org.hibernate.validator.constraints.Range;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.NotEmpty;

public class ContractDto {
    private long contractId;
    @NotEmpty(message = "Select the date you need")
    @JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "d.M.yyyy")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private String date;
    @Range(min = 1, message = "The price cannot be zero")
    private long price;
    @NotEmpty(message = "Event shouldn't be empty")
    private String event;
    private String deliveryService;
    @Range(min = 1, message = "You have to choose a renter")
    private Long person;
    @Range(min = 1, message = "You have to choose a sword")
    private Long sword;

    public ContractDto(long contractId, String date, long price, String event, String deliveryService, Long person, Long sword) {
        this.contractId = contractId;
        this.date = date;
        this.price = price;
        this.event = event;
        this.deliveryService = deliveryService;
        this.person = person;
        this.sword = sword;
    }

    public  ContractDto() {}

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

    public Long getPerson() {
        return person;
    }

    public void setPerson(Long person) {
        this.person = person;
    }

    public Long getSword() {
        return sword;
    }

    public void setSword(Long sword) {
        this.sword = sword;
    }
}
