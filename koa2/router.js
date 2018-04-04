// mount global router

const Router = require('koa-router');
const router = new Router();
const fs = require('fs');
const configure = require('./configure');
const util = require('util');
const  execFile  = util.promisify(require('child_process').exec);

/**
 * COR controls
 */
router.options('/*',(ctx)=>{
    ctx.set('Access-Control-Allow-Headers','Content-Type');
    ctx.set('Access-Control-Allow-Origin','*');
    ctx.set('Access-Control-Allow-Methods','POST, GET, OPTIONS, DELETE, PUT');
    ctx.set('Access-Control-Max-Age','86400');
    ctx.body = '';
});
router.use('/*',async(ctx,next)=>{
    ctx.set('Access-Control-Allow-Origin','*');//must set
    //ctx.debug(ctx.request.body);
		await next();
});


/*
 * funcitions
 */
let getPath = (s) => {
	return `${configure.workSpace}/${s}`;
}
let read = (s)=>{
	let ans = fs.readFileSync( getPath(s), {
	encoding:'utf-8'
	});
	return ans;
}
let write = (res)=>{

};
/*
 * hello
 */
router.get('/hello', async(ctx)=>{
	ctx.good('you r in');
});
/*
 * get
 * mps.txt
 * bom.txt
 * stock.txt
 * consist.txt
 */
const files = [
	'mps',
	'bom',
	'stock',
	'consist',
	'output'
];
router.get('/:filename', async(ctx)=>{
	let name = ctx.params['filename'];
	let i = files.indexOf(name);
	i++;
	if( i>=1 && i <= 4){
		ctx.good(null, read( `${i}${name}.txt`));
	}
	else if(i == 5){
		const {stdout}= await execFile('runlib.cmd', [] );
		let ans =read('5output.txt')
		ans = ans.replace(/\r/g, '');
		ctx.good(null,ans);
	}
	else {
		ctx.bad(null, 'file not found');
	}
});
router.post('/:filename', async(ctx)=>{
	let name = ctx.params['filename'];
	let str = ctx.request.body.fields[name];
	let i = files.indexOf(name);
	i++;
	if( i>=1 && i <= 4){
		filename = getPath( `${i}${name}.txt` );
		let cnt = fs.writeFileSync( filename, str, {encoding:'utf-8'}) ;
		ctx.good(null,str);
	}
	else if( i == 5)ctx.bad('not allowed',null);
	else {
		ctx.bad('file not found', null);
	}
});

module.exports = router;
