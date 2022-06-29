import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import unocss from '@unocss/vite'
import presetUno from '@unocss/preset-uno'
import presetAttributify from '@unocss/preset-attributify'
import presetIcons from '@unocss/preset-icons'
import markdown from 'vite-plugin-markdown'
import eslint from 'vite-plugin-eslint'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
    unocss({
      presets: [
        presetUno(),
        presetAttributify(),
        presetIcons({
          cdn: 'https://esm.sh/',
        }),
      ],
    }),
    markdown(),
    eslint(),
  ],
})
