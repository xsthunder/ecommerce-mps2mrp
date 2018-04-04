const app = require('./koa.js');

const router = require('./router.js');
const KoaBody = require('koa-body');


app
    .use(KoaBody({
        multipart:true
    }))
    .use(router.routes());
    //.use(router.allowedMethods());


const port = require('./configure').port;
app.listen(port);
app.context.log(`tzbei api listen in ${port}`);
