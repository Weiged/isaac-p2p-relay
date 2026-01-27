const proc = Process.mainModule

console.log(`proc --> ${proc.base} ${proc.name}`)

const _32bitSize = 0x400000

const ctx = proc.base.add(0xbf7758 - _32bitSize)

const vCtx = ctx.add(0x8).readPointer()

const vitualTable = vCtx.readPointer()

const flag = ctx.add(4).readPointer()

console.log(`ctx --> ${ctx.readPointer()} ${flag} ${vCtx} ${vitualTable}`)

const vModule = Process.findModuleByAddress(vCtx)
if (vModule) {
    console.log(`vModule --> ${vModule.name} ${vModule.base} ${vModule.size} ${vCtx.sub(vModule.base)}`)
} else {
    console.log(`vModule not found --> ${Memory.queryProtection(vCtx)} ${vCtx}`)
}


if (flag.toInt32() == 1) {
    Module.load("p2p_hook.dll")
}

// for (let i = 0; i < 20; i++) {
//     const func = vitualTable.add(i * 4).readPointer()
//     console.log(`func --> ${func}`)
//     if (i == 0) {
//         const target = Process.getModuleByAddress(func)
//         console.log(`target --> ${target.name} ${target.base} ${target.size} ${func.sub(target.base)}`)
//         let count = 0
//         Interceptor.attach(func, {
//             onEnter(args) {
//                 console.log(`args --> ${args[0]} ${args[1]} ${args[2]} ${args[3]} ${args[4]} ${args[5]} ${args[6]}`)
//                 console.log(`this --> ${this.context.ecx}`)
//                 count++
//                 if (count > 20) {
//                     Interceptor.detachAll()
//                 }
//             },
//         })
//         break
//     }
// }

const steamId = vitualTable.add(8).readPointer()

console.log(`steamId --> ${steamId}`)

const buf = Memory.alloc(8)
const fn = new NativeFunction(steamId, 'pointer', ['pointer', 'pointer'], 'thiscall')
const result = fn(vCtx, buf)
console.log(` getSteamId --> ${buf} ${result} ${buf.readU64()}`)