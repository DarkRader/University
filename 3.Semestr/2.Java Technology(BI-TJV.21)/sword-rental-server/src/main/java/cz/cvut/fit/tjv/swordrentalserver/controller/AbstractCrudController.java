package cz.cvut.fit.tjv.swordrentalserver.controller;

import cz.cvut.fit.tjv.swordrentalserver.business.AbstractCrudService;
import org.springframework.data.repository.CrudRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.function.Function;
import java.util.stream.StreamSupport;

public abstract class AbstractCrudController<E, D, R extends CrudRepository<E, Long>> {
    protected AbstractCrudService<Long, E, R> service;
    protected Function<E, D> toDtoConverter;
    protected Function<D, E> toEntityConverter;

    public AbstractCrudController(AbstractCrudService<Long, E, R> service, Function<E, D> toDtoConverter, Function<D, E> toEntityConverter) {
        this.service = service;
        this.toDtoConverter = toDtoConverter;
        this.toEntityConverter = toEntityConverter;
    }

    @PostMapping
    public D create(@RequestBody D e) {
        System.out.println(toEntityConverter.apply(e));
        return toDtoConverter.apply(service.create(toEntityConverter.apply(e)));
    }

    @GetMapping
    public List<D> readAll() {
        return StreamSupport.stream(service.readAll().spliterator(), false).map(toDtoConverter).toList();
    }

    @GetMapping("/{id}")
    public ResponseEntity<D> readOne(@PathVariable Long id) {
        var res = service.readById(id);
        if (res.isPresent())
            return ResponseEntity.ok(toDtoConverter.apply(res.get()));
        else
            return ResponseEntity.notFound().build();
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable Long id) {
        service.deleteById(id);
    }
}
