"""
Module to run FastAPI application, where API routers are connecting application to API modules.
In other words it is an entry point of the application.
"""
import time
import uvicorn
import logging
from fastapi import FastAPI, Request
from starlette.middleware.cors import CORSMiddleware

from api import documents, document_permission, discussions, comments, evaluations, utils, users
from core import settings
from db import init_db

app = FastAPI(
    title=utils.fastapi_docs.NAME,
    description=utils.fastapi_docs.DESCRIPTION,
    version=utils.fastapi_docs.VERSION,
    openapi_tags=utils.fastapi_docs.get_tags_metadata()
)
app.include_router(users.router)
app.include_router(documents.router)
app.include_router(document_permission.router)
app.include_router(discussions.router)
app.include_router(comments.router)
app.include_router(evaluations.router)

app.add_exception_handler(
    utils.MethodNotAllowedException, utils.method_not_allowed_exception_handler
)
app.add_exception_handler(
    utils.EntityNotFoundException, utils.entity_not_found_exception_handler
)
app.add_exception_handler(
    utils.NotImplementedException, utils.not_implemented_exception_handler
)

origins = ["*"]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s-%(name)s-%(levelname)s: %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)
log = logging.getLogger(__name__)


@app.middleware("http")
async def log_requests(request: Request, call_next):
    start_time = time.time()
    log.info(f"Request: {request.method} {request.url}")

    response = await call_next(request)
    process_time = time.time() - start_time

    log_level = logging.INFO
    if response.status_code >= 500:
        log_level = logging.ERROR
    elif response.status_code >= 400:
        log_level = logging.WARNING
    log.log(level=log_level,
            msg=f"Response: {response.status_code}, Duration: {process_time:.2f} seconds")
    return response


@app.on_event("startup")
async def startup_event():
    """
    Is called on the application startup, before it is ready to accept requests.
    Is used for app initialization, like here it is creating db tables if they are not created.
    """
    log.info(f"Starting {settings.APP_NAME}.")
    init_db()


if __name__ == "__main__":
    uvicorn.run("main:app",
                host=settings.APP_SERVER_HOST,
                port=settings.APP_SERVER_PORT,
                reload=settings.APP_SERVER_USE_RELOAD,
                proxy_headers=settings.APP_SERVER_USE_PROXY_HEADERS)
