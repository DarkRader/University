package cz.cvut.fit.tjv.swordrentalclient.data;

import cz.cvut.fit.tjv.swordrentalclient.model.dto.PersonDto;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import java.util.Arrays;
import java.util.List;

@Component
public class PersonClient {
    private static final String ONE_URI = "/{id}";
    private static final String ROOT_RESOURCE_URL = "http://localhost:8080/persons";

    private final RestTemplate restTemplate;

    @Autowired
    public PersonClient(RestTemplateBuilder restTemplateBuilder) {
        restTemplate = restTemplateBuilder.rootUri(ROOT_RESOURCE_URL).build();
    }

    public PersonDto create(PersonDto personDto) {
        restTemplate.postForLocation("/", personDto);
        return personDto;
    }

    public PersonDto readById(Long id) {
        return restTemplate.getForObject(ONE_URI, PersonDto.class, id);
    }

    public List<PersonDto> readAll() {
        PersonDto[] response = restTemplate.getForObject("/", PersonDto[].class);
        if (response != null) {
            return Arrays.asList(response);
        }
        return null;
    }

    public void update(PersonDto personDto, Long id) {
        restTemplate.put("/" + id, personDto);
    }


    public void delete(Long id) {
        restTemplate.delete("/" + id);
    }
}
